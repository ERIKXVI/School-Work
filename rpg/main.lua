function sleep(n)
    local t0 = os.clock()
    while os.clock() - t0 <= n do end
end

Character = {}
Character.__index = Character

function Character.new(name, age, hp, dmg)
    local self = setmetatable({}, Character)
    self.name = name or "Unknown"
    self.age = age or 0
    self.hp = hp or 100
    self.dmg = dmg or 10
    return self
end

function Character:view()
    print("Your character is done and their name is " .. self.name .. " and their age is " .. self.age .. " years old.")
end

function Character:Start()
    print("Welcome to this RPG!\n")
    print("You will need to start by making your character.\n")
    print("Start by giving your character a name.\n")
    print("Enter the name:")
    self.name = io.read()
    print("Now enter your character's age:")
    self.age = io.read()
    os.execute("cls")
    print("Please wait while we create your character.")
    sleep(10)
    os.execute("cls")
    self:view()
end

function Character:Chapter1()
    print("You get dropped off in the middle of the forest by a van.\n")
    print("You look down on your watch and you see that its midnight.\n")
    print("You look around and you see that there is nothing but dark forest.\n")
    print("You decied that you will walk down one of the paths you see. [1: for path one, 2: for path two, 3: for path three]\n")
    local choice = io.read()
    if choice == "1" then
        print("You decieded to start walking down path one\n")
        print("After about 30 minutes of walking you see light in the distants. Do you go towards the light [y: for yes, n: for no]\n")
        local choice = io.read()
        if choice == "y" then
            print("You start walking towards the light when you get closer you see a bunch of people dancing around a fire while wearing white robs   ")
        end

    end
end

local myCharacter = Character.new()
myCharacter:Start()
