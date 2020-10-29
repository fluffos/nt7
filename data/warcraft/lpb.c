// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m路牌吧[2;37;0m[2;37;0m", ({"lpbs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是袭人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lpb");
        set("owner_name", "袭人");
        set_temp("owner", "lpb");
        set_temp("owner_name", "袭人");
        ::setup();
}
