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

local myCharacter = Character.new()
myCharacter:Start()
