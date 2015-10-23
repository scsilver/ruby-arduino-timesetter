require "serialport"
require 'pusher'

port_str = "/dev/tty.usbmodemfd131"
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE
greeting = ""
count = 0
t = Time.now
sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

#just read forever
while true do
  if count == 0
    if (i = sp.gets.chomp)        # see note 2
      sp.flush

      puts i
      sleep 1
      sp.puts(t.to_i.to_s)
      puts "Unix Time sent to Arduino: " + t.to_i.to_s
      i = ""
      count = count + 1

      #puts i.class #String

    end
  end

  if (i = sp.gets.chomp)        # see note 2
     sp.flush

     puts i
     sleep 1
     greeting = "Hi Arduino"
     sp.puts(greeting)
     puts greeting
     i = ""

     #puts i.class #String

   end


end

sp.close
