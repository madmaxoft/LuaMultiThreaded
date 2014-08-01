
-- thread1.lua

-- Implements the first thread for debugging



function Run()
	print("Hello from thread1")
	local EndTime = os.clock() + 3
	while (os.clock() < EndTime) do
		io.write("1")
	end
	print("thread1 is now ending")
end




