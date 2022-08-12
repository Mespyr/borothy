import json
import io
from discord.ext import commands

# get settings from file
setting_file = io.open("settings.json", "r")
settings = json.load(setting_file)
setting_file.close()

# create borothy
bot = commands.Bot(command_prefix='!')

# run when bot is online
@bot.event
async def on_ready():
    print(f'{bot.user} has connected to Discord!')

# run on every message
@bot.event
async def on_message(message):
    if message.author == bot.user: return
    
    if message.content.strip()[0] == settings["prefix"]:
        # get command name
        command = message.content.split()[0]
        if len(command) == 1: return
        else: command = command[1:]
        
        # get command argv
        command_list = message.content.split()
        if len(command_list) < 2: argv = []
        else: argv = command_list[1:]
        
        # get user's role
        user_role_id = message.author.top_role.id

        # clear channel
        if command == "purge":
            if user_role_id in settings["perms"]: await message.channel.purge()
            else: await message.channel.send(f"```Warning: You do not have permisson to use '{command}'.```")

        # add person to sacrifice to borothy
        # !add <first name> <last name or last initial> <tier level>
        elif command == "add":
            if user_role_id in settings["perms"]:
                if len(argv) < 3:
                    await message.channel.send(f"```Error: not enough arguments for '{command}'.```")
                else:
                    name = argv[0] + " " + argv[1]
                    tier = argv[2]
                    if tier not in ("a", "b", "c", "d"):
                        await message.channel.send(f"```Error: '{tier}' is not a tier level.```")
                    else:
                        tier_channel = bot.get_channel(settings["tiers"][tier])
                        if tier_channel: await tier_channel.send(name)
            else: await message.channel.send(f"```Warning: You do not have permisson to use '{command}'.```")

        else:
            await message.channel.send(f"```Warning: '{command}' is not a known command.```")


# run bot
bot.run(settings["token"])
