// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老虎[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "男性");                
        set("long", "小老虎[2;37;0m
它是刘元晋的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lyjin");
        set("owner_name", "刘元晋");
        set_temp("owner", "lyjin");
        set_temp("owner_name", "刘元晋");
        ::setup();
}
