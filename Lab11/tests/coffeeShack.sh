#!/usr/bin/expect

set timeout 1
spawn ./coffeeShack
expect_after timeout { puts ""; exit 1 }
match_max 100000
expect -exact "Welcome to Coffee Shack, can I get you \[l\]arge, \[m\]edium, or \[s\]mall coffee? "
send -- "m\r"
expect -exact "m\r
Would you like to add \[s\]ugar, \[c\]ream, \[h\]oney, or \[d\]one? "
send -- "c\r"
expect -exact "c\r
As a junior barista, I'm afrad I'm not qualified to add cream to your drink.\r
Fetching a senior barista...\r
Senior barista adding cream to your drink.\r
Would you like to add \[s\]ugar, \[c\]ream, \[h\]oney, or \[d\]one? "
send -- "h\r"
expect -exact "h\r
As a junior barista, I'm afrad I'm not qualified to add honey to your drink.\r
Fetching a senior barista...\r
As a senior barista, I'm afrad I'm not qualified to add honey to your drink.\r
Fetching a manager...\r
Would you like to add \[s\]ugar, \[c\]ream, \[h\]oney, or \[d\]one? "
send -- "d\r"
expect -exact "d\r
Can I get your name? "
send -- "Alex\r"
expect eof
