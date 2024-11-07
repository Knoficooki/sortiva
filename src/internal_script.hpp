#pragma once

inline const char* std_intern_sorting_script = R"(
-- bubble sort
function bubble_sort()
	isSorted = false
	while isSorted == false do
		movedElements = 0
		for x=1, list:size(), 1 do
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