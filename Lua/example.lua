require "core"

y = 2
x = 2
oldx = 2
oldy = 2

function turn()
  x = x + 1
  y = y + 1
  move(2, 2, 2, 2)
  oldx = oldx+1
  oldy = oldy+1
end