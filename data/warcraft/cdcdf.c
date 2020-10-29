// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是玄无天的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cdcdf");
        set("owner_name", "玄无天");
        set_temp("owner", "cdcdf");
        set_temp("owner_name", "玄无天");
        ::setup();
}
