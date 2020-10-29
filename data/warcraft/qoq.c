// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小尾巴[2;37;0m[2;37;0m", ({"oqo"}));        
        set("gender", "女性");                
        set("long", "偷偷露出来[2;37;0m
它是路人乙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qoq");
        set("owner_name", "路人乙");
        set_temp("owner", "qoq");
        set_temp("owner_name", "路人乙");
        ::setup();
}
