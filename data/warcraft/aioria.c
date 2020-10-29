// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m东海三太子[2;37;0m[2;37;0m", ({"whitedragon"}));        
        set("gender", "男性");                
        set("long", "小白龙[2;37;0m
它是艾叶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aioria");
        set("owner_name", "艾叶");
        set_temp("owner", "aioria");
        set_temp("owner_name", "艾叶");
        ::setup();
}
