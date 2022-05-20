import json
import io
import discord

# get settings from file
setting_file = io.open("settings.json", "r")
settings = json.load(setting_file)
setting_file.close()

# create borothy
client = discord.Client()

@client.event
async def on_ready():
    print(f'{client.user} has connected to Discord!')

# commands
@client.event
async def on_message(message):
    if message.author == client.user: return
    
    if message.content.strip()[0] == settings["prefix"]:
        command = message.content.split()[0]

        if len(command) == 1: return
        else: command = command[1:]

        if command == "purge":
            await message.channel.purge()
        else:
            await message.channel.send("```Warning: '" + command + "' is not a known command.```")


# run bot
client.run(settings["token"])
