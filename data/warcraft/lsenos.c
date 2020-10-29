// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小茶茶[2;37;0m[2;37;0m", ({"lvcha"}));        
        set("gender", "男性");                
        set("long", "飘飘[2;37;0m
它是笑不哭的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lsenos");
        set("owner_name", "笑不哭");
        set_temp("owner", "lsenos");
        set_temp("owner_name", "笑不哭");
        ::setup();
}
