// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火红朱雀[2;37;0m[2;37;0m", ({"hhzq"}));        
        set("gender", "女性");                
        set("long", "火红朱雀[2;37;0m
它是以太飘雪的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "etherl");
        set("owner_name", "以太飘雪");
        set_temp("owner", "etherl");
        set_temp("owner_name", "以太飘雪");
        ::setup();
}
