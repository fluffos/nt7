// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "这是互博美眉的坐骑——朱雀。[2;37;0m
它是互博美眉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hbmm");
        set("owner_name", "互博美眉");
        set_temp("owner", "hbmm");
        set_temp("owner_name", "互博美眉");
        ::setup();
}
