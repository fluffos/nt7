// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("符号[2;37;0m[2;37;0m", ({"info"}));        
        set("gender", "男性");                
        set("long", "符号[2;37;0m
它是无聊人生的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "keenchat");
        set("owner_name", "无聊人生");
        set_temp("owner", "keenchat");
        set_temp("owner_name", "无聊人生");
        ::setup();
}
