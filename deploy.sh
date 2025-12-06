#!/bin/bash
sudo cp -Trf ./client/html /var/www/seaport/html
sudo cp -Trf ./client/css /var/www/seaport/css
sudo cp -Trf ./client/js /var/www/seaport/js

sudo make -C server install

sudo cp -f seaport.conf /etc/apache2/sites-available/seaport.conf
sudo a2enmod ssl
sudo a2enmod cgi
sudo a2ensite seaport.conf
sudo systemctl restart apache2

