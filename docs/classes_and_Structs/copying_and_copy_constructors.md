# Copying and Copying Constructors in C++

## Intro

Copying refers to us copying data copying memory when we literally want to copy
one object or primitive or just a piece of data from kind of one place into
another

- We literally have two copies of it a lot of the time we want to
  copy objects that we can modify them in certain ways but if if we can avoid
  copying if we can avoid unnecessary copying.

- because we just want to read the
  value or we want to actually modify an existing object we absolutely want to do
  that because copying takes time.

- Copying can be both a really useful thing
  that we actually need to make our program work the way that we wanted to but on
  the flip side unnecessary copying is bad and we want to avoid that as much as
  possible because it wastes performance.

- So understanding how copying actually
  works in C++ and how to get it to work and also how to avoid getting it to work
  or avoid copying when you don't want to copy is very important to understanding
  the language and being able to write C++ code efficiently and correctly.

- Demonstrate this in an effective way I'm actually going to write a full on
  example window write a class it's gonna be a string class and we're gonna talk
  about how copying affects that and what we can do to to both remove copying when
  we don't want copying but also even you know add copying so that we can copy
  correctly so first of all let's jump Copying

## My Understanding

```cpp

 struct Vector2{
     float x, y;
 }

 +-------------------------------+
 |         main function         |
 +-------------------------------+
   int main(int argc , char* argv[]){
           int a = 2;                             <--  Let's declare a
                                                       variable a primitive type like a
           int b = a;                             <--  then I declare another primitive type
                                                        called B and I assign it to a and what
                                                        I'm actually doing is I'm creating a
                                                        copy of it so a and B are two separate
                                                        variables ( which have different memory addresses)

          // Alloacted on stack
          // Similarly the copying is happening here as well
          Vector2 v1(10,20);
          Vector2 v2 = v1;

           std::cin::get();
   }

```

- How about copying a vector allocated on heap?

```cpp

 struct Vector2{
     float x, y;
 }


 +-------------------------------+
 |         main function         |
 +-------------------------------+
   int main(int argc , char* argv[]){

          // Similarly the copying is happening here as well
          Vector2 v1 = new Vector2(10,20);
          Vector2 v2 = v1; // Here we copy the pointer not the ojbect of v1 itself.

           std::cin::get();
    }
```

### Assign operator with copying

1. You almost always copy an object when you are using the `assign operator`
   `=`. But with two exceptions:

- When you copy a pointer, you are copying it not the object which it refers to
  (see the example above).

- When you are using `references`, you are not doing a copying

```cpp
int a = 10;
int& ref_a = a;     <-- Here you are now copying rather than create a reference.
```

### Demo - Creating a string class to demonstrate the copying

I'll do something like
Victor 2a equals new vector2 we're
actually going to need to either define
a constructor or in this case well it
will be empty if I then try and do
something like a sine B with with a this
is going to be something completely
different because the vector two right
now is a pointer which means that by
writing back to point a B equals a what
I'm still copying something but I'm not
copying the actual vector which can
track it which contains the x and y
variables I'm actually copying the
pointer so now I have two pointers which
essentially have the same value of
course because they're copies they point
to different things find it something
like B plus plus or whatever to modify
the pointer my a pointer would still be
intact but if I access the memory at
that address and set it to something in
this case is kind of going to affect
both a and B because at the moment a and
B are both pointing to the same memory
address and what I'm doing here is I'm
not affecting the pointer I'm affecting
the memory address so that's just
something important to note when you
actually do write any equals when you
write when you use the assignment
operator and you set a variable equal to
another variable you are always well
always asterisk you're always copying
the value the asterisk was there for
references because with references if
you assign a reference to something else
you can't reassign references when you
copy I guess a reference or you assign
one reference to another reference
you're actually changing the underlying
thing that's pointing to because
references are just aliases so kind of
with the exception of references
whenever you write code where one
variable is assigned another variable
you are always copying it it's just with
the case of pointers you're copying the
pointer that that memory address then
muted the numeric memory address the
number rather than the actual memory at
the pointer if that makes sense so with
that in mind let's write a string class
and see about how we can make that
copyable and what challenges we might
face with that so I'm going to write a
class called string now I'm going to
write this string class in a very kind
of well I guess also called primitive
C++ way I'm not going to be using like
STD vector or anything like that or
smart pointers I'm just going to write a
base kind of string class implementation
that is using just the raw metal kind of
C++ features and that's necessary
because if I start using modern modern
kind of C++ features to write this bus
then it is actually going to automate a
lot of this stuff for me and in this
case it's not going
demonstrate my point about copying very
well so just keep that in mind this
isn't how I would necessarily write a
string class nowadays but it is a way to
do it and it's going to be a kind of
nice bare metal Wayne is certainly not
going to be slow and if I don't probably
be faster than if I was to use modern
see what boss pages so a string is made
String
up of an array of characters so the
first thing that I'm going to do is
place down an array of characters I'm
going to write a char pointer that's
called M buffer and this was going to
point to my buffer of chars I'm also
going to keep track of how big the
string is by writing a variable called
size here okay that should be enough so
the constructor for string is going to
take in a constant char which we'll call
string constant a pointer called string
first thing we're going to do is
calculate how long the string is so that
we can copy the data from the string
into our buffer so I'm just going to use
a see function called sterlin or string
length to actually get the size of this
string now that I've got the size I know
how big I want my buffer it's going to
be these size of the string so new char
em size now we actually have to allow
for the null termination character as
well so this should be +1 but I'm
deliberately not going to write that so
that you guys can see what happens so
the next step is going to be copy the
value from this pointer into our actual
buffer so that our buffer is populated
with all our characters I could write a
for loop here just to keep it really
simple something like this really simple
to go through every character that we
have in here and copies at one by one
like so however a much cleaner way to
write this is just to use mem copy
someone to type in mem copy the
parameters for this is the other
destination that goes first so don't
screw that up the destination the source
and the size so the destination is going
to be M buffer the source is going to be
string and the size is in bytes so how
many bytes do we want to copy m size
because at the moment each character is
one byte of memory now we are missing
that null termination character keep
that in mind but let's write something
that can at least print our string and
something that will they will be able to
use to print our spring so I want to be
able to use this with standard that C
out so what I'm going to do is write an
overload for that operator so we'll
write STD outlet stream operator shift
left STD output stream stream our string
classes will be a constant string
reference string is going to return our
stream and before it does that is just
going to show
stringbuffer which is a method I'm just
about a ride into there we could also
make this operator a friend of this
class and then we'd be able to call em
buffer from this function because it
would be a friend in fact I think I
might do it that way instead of doing
get buffer I might just copy this
declaration pop it in here name it a
friend like so and what that means is
that I'll actually be able to write code
such as this so you can see I'm
accessing a private member if this code
wasn't present here that wouldn't be
acceptable because M buffer is a private
member of the string class but since
we've declared this operator as a friend
we can now write code like this
beautiful so if I go back to men and I
write my string variable here I'll just
set it equal to shadow and then I'll
just pop it in to see house like that
all right looks pretty good hit f5 and
there we have our shadows string
printing you can see it's accompanied by
a lot of other random characters because
we don't have that null termination
character so let's go ahead and add that
in the way I'm going to do that is just
when I allocates a buffer I'm going to
do M size plus 1 you could also use
string copy which one I'm going to talk
about for now but I'm just gonna
allocate m / + 1 to make room for that
we know that this string does have a
null termination character so to make
this easy I could write code like this
which kind of seems to copy over the
length of this if I hit at 5 this will
work but this is working under the
assumption that this string that this
child pointer is actually properly not
terminated if we can't guarantee that
just to be a bit safe I'm just going to
set m buffer m size here equal to 0 like
this manually adding my own null
termination character at the end of this
hit f5 and we should be good and you can
see that we are well finally writing
some actual code in this series really
excited about that hope I'm not going
too fast I'm kind of trying to rush
through this this is mostly basic kind
of there's me kind of setting up the
string class so that I can actually show
you the copying which is what this
videos about so if you have any
questions about anything I wrote in this
kind of segment or another I guess maybe
other sections of this video where I
rush through things the best place to
ask these questions is to join my
discord server
there'll be a link in description if you
just go to the channel to calm slash
discord then you'll be able to join that
server and you can talk to a lot of
people about how all this works and I'll
be there as well to explain this stuff
too if you don't get it
Memory leak
okay so we've got a basic set up here
and everything looks pretty good we've
actually got a bit of a memory leak here
that we should really fix and that is
when we allocate this new char right
here we never delete it if we use a
smart pointer or a vector we wouldn't
need to but since we're using the new
keyword and we're allocating a raw array
we have to actually delete it over here
by calling delete buffer in the
destructor okay fantastic so if we
launch this code we'll just verify that
our program Gemini successful and you
can see it does now let's try to copy
this string so the way so in this
scenario maybe I want to print out this
string and then later on I actually want
to print I want to make an adjustment to
this string I'll just call this second
for this our second string let's assign
this to this string for now and let's
try some code that prints both of these
okay let's hit f5 you can see that we
get channel pretty twice which is
exactly what we expect everything seems
to be working once hit enter to proceed
past this scene get and terminate our
application oh look at that it crashed
and if you look at the Cole stack which
I'm going to bring over here so that you
can actually see it it looks kind of
cryptic isn't it's inside anti DLL since
I've kernel32.dll well we don't know
what's going on it looks a bit weird
what on earth happened so if I terminate
my application
let's talk about this what we did here
is we copied the string and when we copy
the string what C++ does for us
automatically is it just takes whatever
members there are here which is
basically what what this class is made
up it's made but it's made up of a child
pointer and an on side end and it takes
those values and it copies them into a
new memory address which contains this
string the second string of ours now
here's the problem what we have now in
memory is two strings and since they did
it did a direct copy something called a
shallow copy what it did is it copied
this pointer so we have two strings in
memory which of course have the exact
same child pointer value in other words
the memory address the memory address of
this buffer is the same for both of
these strings
and we get the crash because when we
come over here to the end of this scope
and both of these strings get destroyed
the destructor gets called and we end up
deleting this buffer twice so we're
trying to free the same block of memory
twice that's why we get a crash because
the memory has already been freed it's
not ours
we can't free it again so perhaps a
better example to demonstrate how this
really is the same
I'm just putting a breakpoint here
hitting f5 and then being able to mouse
over both of these you'll see that in
this case M buffer has a memory address
ae 0 4 4 0 & 4 second we also have a e0
4 4 0 so clearly the pointer is the same
apart from doing that let's say that we
actually want to modify the second
string so I maybe instead of I'll change
the third character from E to a to get
China which which you guys love will
access the second index and assign it to
a of course in order to get this
operator to work for the string class
we'll have to write it so here I'm just
going to write something that returns a
char reference operator index operator
unsigned int index we're not going to do
any kind of safety checks to make sure
we're inside the bounds we're just going
to return and buffer at index to keep it
nice and simple ok this works let's hit
f5 and check this out there boys charnot
so why why is that happy and we get and
of course we also get the crash so why
is this happening it looks like we've
copied it but we haven't what we
actually need to do is allocate a new
char array to store the copied string
right because what we're doing now is
we're copying the the pointer and what
we have is two string objects pointing
to the exact same buffer of memory which
means that when we either try and change
one of them it changes both of them
because they're pointing to the same
block of memory or when we delete one of
them it's gonna delete both of them
because well they're pointing to the
same block of memory we want to actually
copy that block of memory we want the
second string to have its own pointer to
have its own unique block of memory
that's pointing to so that when we
either modify or delete the second
string it doesn't touch the first string
and vice versa and the way that we can
do that is by performing something
called a deep copy meaning we're
actually copying the entire object not
just the kind of shallow like features
that we see on the very top such as what
actually makes up the object because if
you look at the object in memory it's a
pointer and an int that's all it is but
a shallow copy is not gonna go to the
contents of the pointer or where the
point is pointing to and actually copy
that as well a deep copy is by
definition going to copy the object in
its entirety so how do we make a perform
a deep copy well of course we could
write our own clone like method or
function on it
that and have it just returned a new
string which contains anyway that's I
don't even want to explain that because
that's not the way you do it the way
that you do it is you write a copy
constructor and a copy constructor is a
constructor that gets called for that
second string when you actually copy it
so when you assign a string to an object
that is also a string when you try to
create a new variable and you assign it
with another variable which has the same
type as a variable that you're actually
creating you're copying that variable
and thus you're calling something called
the copy constructor let's write one of
Copy constructor
these now C++ by default will actually
provide you with a copy constructor you
can do several things with this copy
constructor the definition or the
declaration for this copy constructor
the signature is a constructor that
takes in a reference a const reference
to the same class so string costs string
reference and then you can call it
something like other because that's a
sensible name so as i say this a plus
plus actually supplies you with one of
these automatically and what that does
is literally a mem copy it's just going
to copy the memory of the other object a
shallow copy into these members so in
other words if we were to write a one of
these constructors ourselves it would
probably look something like this and
buffer other door and buffer and then
emphasize other door size okay that's
pretty much that is exactly what it was
cost kind of supplies us with
Disable copy constructor
so that's not gonna cut it here
we don't just want to copy the pointer
we want to copy the memory at the
pointer now if we decide that we don't
want a copy constructed because we don't
want to allow copying we can just
declare this copy constructor as equals
delete and you can see down over here
this code will not compile anymore
this is exactly what unique point it
does if you look at my other video on
smart pointers that are released like
two days ago
linked up there you saw this in action
when we talked about unique pointers so
Deep copy
that's how we kind of disable that but
what we want to do here is to find our
own copying instructor which does that
deep copy so what I'll do over here is
I'll copy size because well that is that
is an integer we can just shallow copy
that and then over here what I'm going
to do is just simply allocate a new
buffer we already know how big it needs
to be it needs to be M size which we've
already signed up here plus one we know
that we're copying from another string
object so what we really need to do here
is simply copy the other buffer so
Arthur dot M buffer into the buffer for
this string class and then we'll set
this to be precise plus one over here I
can just write this because I know that
the other size the other string is
already gonna have that null termination
character because it's a string and it
has to and that's it that's all the code
that I have to write to perform an
actual deep copy in this case so now if
Running the code
I scroll down here to my code and I hit
f5 to run my code the first thing you'll
notice is that I actually have China and
China written here so the first string
did not change how awesome is that when
we change the second string it didn't
change our first string that's pretty
cool and then when I hit enter it
doesn't crash our program terminates
successfully so as we discussed if you
Printing the string
write code like this it will of course
copy your string if you decide to
actually write a function here that
prints our string so I'll just write
void print string I'll pass in a string
like this and I'll just call STD C out
string and we end up using this function
instead of these C outs I'll get rid of
these C outs and I'll just call print
string string and print string second if
I hit f5 everything appears to work but
what what we're actually doing is we're
actually needlessly copying this if we
come over here to the copy constructor
and just write a quick message here
says copied string it kind of looks like
maybe we're doing one copy over here but
we're actually doing two more when we
pass it into this function and we can
prove it by hitting out five you can see
that we get three string copies
happening ridiculous because when we
don't want to be doing that what's
actually happening is every time we copy
a string we allocate memory on the heap
copy all that memory and then at the end
of it we free it that's completely
unnecessary what we actually want to do
is just pass the existing string into
this print string function because we
know that we're not going to need to
copy we don't need another copy of it we
can just reference the existing one and
Staking a reference
the way that we do that is by passing
this by reference which we can do by
staking a reference here now this class
will actually not be modifying the
string so what we should do really is
market as a Const reference if we don't
mark it as Const not only does that mean
that we can actually edit this so in
other words I can just do write code
like this if it wasn't marked as Const
maybe let's make us a character just so
it's clearer but because if it if it's
not constant I can actually edit the
existing string and if it's constant con
means that we can't pass temporary our
values into the actual function we'll
talk about L values and our values soon
I don't even want to get into them now
because it's actually quite a complex
topic and this isn't meant to be about
that but eventually all I'm saying here
is that if we change this function
signature to accept a cost reference of
a string rather than just a string then
if I hit f5 you can see we only have one
copy and that one copy happens over here
when we assign a second with the value
of string because that actually needs to
be a copy because we're trying to create
two different strings if we suddenly
Summary
decide in the print string function oh
actually I do want to copy guess what we
can actually do that just by typing in
code like this so what I'm trying to
tell you is always pass your objects by
constant reference always we'll talk
about really kind of being depth
optimization about that in the future
because maybe in some situations it
actually might be faster to copy but for
all intents and purposes is better than
a basic level always pass your objects
by constant reference because the
function itself that you're writing you
can decide if you want to copy in that
function but there's no reason for you
just to be throwing around copies all
the time that's close it program down
it's stupid whenever you pass a string
doesn't matter if it's your own string
class or if this is just STD string
always always plus that by constants
sometime in the future I want to make a
quick video that actually talks about
passing by Const reference and a lot
more detail and what advantages it gives
us apart from reducing copies but for
now just kind of keep that in mind
anyway I hope you guys enjoyed this
video about copying hopefully you guys
are experts now on how copying actually
works and say bus blast went to use it
how to write a class that supports
copying correctly you need to specify
that copy constructor and hopefully you
also know what copying does now and how
you can and help preventing it or how
mitigating it can kind of make your
program run a lot faster because it's
not just copying data and wasting CPU
cycles is doing that for absolutely no
reason at all if you guys liked this
Outro
series and you want to support it and
you want to see more episodes and you
can do so by going to patreon.com 4/2
Cherno you'll be able to see episodes
earlier for example i think this video
is probably gonna get out a day earlier
for patrons than it is for anyone else
you'll also get access to a private disc
or channel where we kind of talk about
these episodes and what goes into them
and plan them and all that fun stuff I
think this was kind of the first video
where we actually wrote quite a bit of
code and got some stuff done so I hope
you enjoy videos like this because now
that we kind of know the basics of C++
apart from little tips and tricks I
guess here and there we're gonna be
actually writing code now and especially
when I start the new series that I'm
going to if you guys haven't seen the
video I made on the weekend about the
new series I'm starting check that out
for sure link up there but when we start
those series this is what they're gonna
be like so if you're excited about that
hit the like button support this series
and not and everything I do on patreon
because that's gonna be sure that I can
make more videos and I will see you guys
in the next episode goodbye
[Music]
[Music]

## References

- [Copying and Copy Constructors in C++ - The Cherno](https://www.youtube.com/watch?v=BvR1Pgzzr38&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=44)
