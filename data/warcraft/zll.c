// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m风风[2;37;0m[2;37;0m", ({"baihuuu"}));        
        set("gender", "女性");                
        set("long", "$HIC$风风[2;37;0m
它是聆聆的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zll");
        set("owner_name", "聆聆");
        set_temp("owner", "zll");
        set_temp("owner_name", "聆聆");
        ::setup();
}
