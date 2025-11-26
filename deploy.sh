#!/usr/bin/bash

sudo cp -rf ./client/html /var/www/seaport/html
sudo cp -rf ./client/html /var/www/seaport/css
sudo cp -rf ./client/html /var/www/seaport/js

sudo make -C server install

sudo cp -f seaport.conf /etc/apache2/sites-available/seaport.conf
sudo a2ensite seaport.conf
sudo systemctl restart apache2

