
-- thread3.lua

-- Implements the third thread for debugging



return function()
	print("thread3 running")
	local EndTime = os.clock() + 3
	while (os.clock() < EndTime) do
		io.write("3")
	end
	print("thread3 done.")
end




