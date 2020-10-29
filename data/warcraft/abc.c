// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("搅屎棍[2;37;0m[2;37;0m", ({"iiip"}));        
        set("gender", "女性");                
        set("long", "(⊙o⊙)哦[2;37;0m
它是美妙美的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "abc");
        set("owner_name", "美妙美");
        set_temp("owner", "abc");
        set_temp("owner_name", "美妙美");
        ::setup();
}
