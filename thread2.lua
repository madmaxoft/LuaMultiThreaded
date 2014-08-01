
-- thread2.lua

-- Implements the second thread for debugging




function Run()
	print("This is thread 2, about to sleep.")
	sleep(500)
	print("Thread 2 has finished sleeping, will now run.")

	local EndTime = os.clock() + 3
	while (os.clock() < EndTime) do
		io.write("2")
	end
	print("thread 2 done.")
end




