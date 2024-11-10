#pragma once

inline const char* std_intern_sorting_script = R"(
-- bubble sort
function bubble_sort()
	local isSorted = false
	while not isSorted do
		local movedElements = 0
		for x = 0, list:size() - 2 do
			if list:greater(x, x+1) then
				movedElements = movedElements + 1
				list:swap(x, x+1)
			end
		end
		if movedElements == 0 then
			isSorted = true
		end
	end
end

function do_nothing()
end

-- other functions


)";