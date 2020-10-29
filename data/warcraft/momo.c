// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "这是一只千年火龙王 实力非常的强悍![2;37;0m
它是陌陌的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "momo");
        set("owner_name", "陌陌");
        set_temp("owner", "momo");
        set_temp("owner_name", "陌陌");
        ::setup();
}
