// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m慈禧[2;37;0m[2;37;0m", ({"whistlent_cixi"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是宗棠的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zongtang");
        set("owner_name", "宗棠");
        set_temp("owner", "zongtang");
        set_temp("owner_name", "宗棠");
        ::setup();
}
