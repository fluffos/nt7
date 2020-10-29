// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("三轮车[2;37;0m[2;37;0m", ({"xdemia"}));        
        set("gender", "女性");                
        set("long", "劳动工具[2;37;0m
它是壮士一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "demia");
        set("owner_name", "壮士一");
        set_temp("owner", "demia");
        set_temp("owner_name", "壮士一");
        ::setup();
}
