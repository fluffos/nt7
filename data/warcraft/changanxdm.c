// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "sleepbag[2;37;0m
它是长三安的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "changanxdm");
        set("owner_name", "长三安");
        set_temp("owner", "changanxdm");
        set_temp("owner_name", "长三安");
        ::setup();
}
