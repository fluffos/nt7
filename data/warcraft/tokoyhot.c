// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m女优[2;37;0m[2;37;0m", ({"actress"}));        
        set("gender", "女性");                
        set("long", "这是一个浑身赤裸的av女优，看起来面上堆满疲倦。[2;37;0m
它是东京热的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tokoyhot");
        set("owner_name", "东京热");
        set_temp("owner", "tokoyhot");
        set_temp("owner_name", "东京热");
        ::setup();
}
