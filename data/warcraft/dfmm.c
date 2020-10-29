// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小红[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "一只通红的朱雀[2;37;0m
它是东方妹妹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dfmm");
        set("owner_name", "东方妹妹");
        set_temp("owner", "dfmm");
        set_temp("owner_name", "东方妹妹");
        ::setup();
}
