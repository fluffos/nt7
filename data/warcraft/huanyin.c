// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m邪[1;34m眸[35m白[1;33m虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是叶幻音的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "huanyin");
        set("owner_name", "叶幻音");
        set_temp("owner", "huanyin");
        set_temp("owner_name", "叶幻音");
        ::setup();
}
