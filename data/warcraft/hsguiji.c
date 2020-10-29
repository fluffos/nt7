// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "我的宝马[2;37;0m
它是亢龙有悔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hsguiji");
        set("owner_name", "亢龙有悔");
        set_temp("owner", "hsguiji");
        set_temp("owner_name", "亢龙有悔");
        ::setup();
}
