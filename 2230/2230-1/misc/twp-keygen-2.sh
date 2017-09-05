#!/usr/bin/env python

import os
import mimetypes
import getpass
import smtplib
import subprocess
from smtplib import SMTPAuthenticationError
from email.mime.multipart import MIMEMultipart
from email import encoders
from email.message import Message
from email.mime.audio import MIMEAudio
from email.mime.base import MIMEBase
from email.mime.image import MIMEImage
from email.mime.text import MIMEText

# twp-client.py
#
# This script serves to be a hands free client
# program which creates a default RSA Key for
# students if they don't exist, then e-mails their
# public key to the appropriate server for registration

#####
# Script Variables
#####
MAX_PASSWORD_ATTEMPTS = 3
class_emails = {
	'a' : 'trenarycs223@gmail.com',
	'b' : 'trenarycs224@gmail.com'
}
fileToSend = os.path.expanduser("~/.ssh/id_rsa.pub")

#####
# Begin Script
#####
class_arg = raw_input('2230(a) or 2240(b)?: ')
emailto = class_emails.get(class_arg, 'err')
if emailto == 'err':
	print 'Invalid option, please enter a or b'
	exit(1)

emailfrom = raw_input('Enter your wmich email: ')
username = raw_input('Enter your Bronco NET ID: ')

#####
# Validate username and password
#
# we will invalidate the email session after we validate the user session
# leaving a connection open during work would be a bad idea
#####
ct = 0
while True:
	if ct == MAX_PASSWORD_ATTEMPTS:
		print 'Authentication failed'
		server.quit()
		exit(1)

	password = getpass.getpass('Enter your wmich password: ')
	server = smtplib.SMTP("smtp.wmich.edu:587")
	server.starttls()

	try:
		server.login(username,password)
	except SMTPAuthenticationError:
		print 'Incorrect username/password combination, please try again.\
		Attempt {0} of {1}.'.format(ct+1, MAX_PASSWORD_ATTEMPTS)
		ct = ct + 1
		server.quit()
		continue
	server.quit()
	break

print 'Working...'

if not os.path.isfile(os.path.expanduser('~/.ssh/id_rsa')) and not os.path.isfile(os.path.expanduser('~/.ssh/id_rsa.pub')):
	print 'RSA Keys don\'t exist, creating one'
	subprocess.Popen('ssh-keygen -b 2048 -t rsa -f ~/.ssh/id_rsa -q -N ""', shell=True)

msg = MIMEMultipart()
msg['From'] = emailfrom
msg['To'] = emailto
msg['Subject'] = '[KEYS]'

ctype, encoding = mimetypes.guess_type(fileToSend)
if ctype is None or encoding is not None:
	ctype = "application/octet-stream"

maintype, subtype = ctype.split("/", 1)

# check for pub file type
# if ctype == 'application/x-mspublisher':
fp = open(fileToSend)
#	 # Note: we should handle calculating the charset
attachment = MIMEText(fp.read(), _subtype=subtype)
#	 fp.close()
# else:
#	 print 'invalid file type [{0}] for id_rsa.pub'.format(ctype)
#	 exit(1)

attachment.add_header('Content-Disposition', 'attachment', filename='id_rsa.pub')
msg.attach(attachment)

# create smtp session and send the email
server = smtplib.SMTP("smtp.wmich.edu:587")
server.starttls()
server.login(username,password)
server.sendmail(emailfrom, emailto, msg.as_string())
server.quit()

print 'Success!'
