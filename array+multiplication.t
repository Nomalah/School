var t := Time.Elapsed
var num1:flexible array 1..1 of int
num1(1):=1
     var num2:flexible array 1..1 of int
num2(1):=2
var ans:flexible array 1..1 of int
for m:1..64
     new ans, upper(num1)+upper(num2)
     for n:1..upper(ans)
          ans(n):=0
     end for
          
     for x:1..upper(num2)
          for y:1..upper(num1)
               var s:=intstr(num2(x)*num1(y))
               if length(s)<2 then
                    s:= "0"+s
               end if
               ans(y)+= strint(s(2))
               new ans,y+1
               ans(y+1):= strint(s(1))
               
          end for
     end for
          
     if ans(upper(ans)) = 0 then
          new num1 , upper(ans)-1
          for decreasing n:upper(ans)-1.. 1
               put ans(n)..
               num1(n):=ans(n)
          end for
               
     else
          new num1 , upper(ans)
          for decreasing n:upper(ans).. 1
               put ans(n)..
               num1(n):=ans(n)
          end for
     end if
     put""
end for
put Time.Elapsed - t