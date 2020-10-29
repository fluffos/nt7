// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("笨头虎[2;37;0m[2;37;0m", ({"littletiger"}));        
        set("gender", "女性");                
        set("long", "笨头虎[2;37;0m
它是胖头胖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pangtou");
        set("owner_name", "胖头胖");
        set_temp("owner", "pangtou");
        set_temp("owner_name", "胖头胖");
        ::setup();
}
