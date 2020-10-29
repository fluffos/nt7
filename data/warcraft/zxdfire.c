// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火焰神兽[2;37;0m[2;37;0m", ({"firefire"}));        
        set("gender", "男性");                
        set("long", "天鸟[2;37;0m
它是火火儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zxdfire");
        set("owner_name", "火火儿");
        set_temp("owner", "zxdfire");
        set_temp("owner_name", "火火儿");
        ::setup();
}
