// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m环球美人之王[2;37;0m[2;37;0m", ({"meiren"}));        
        set("gender", "女性");                
        set("long", "丰腰肥臀[2;37;0m
它是好美人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lshenlong");
        set("owner_name", "好美人");
        set_temp("owner", "lshenlong");
        set_temp("owner_name", "好美人");
        ::setup();
}
