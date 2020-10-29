// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m朱雀[2;37;0m[2;37;0m", ({"mylove"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是雪凝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xuen");
        set("owner_name", "雪凝");
        set_temp("owner", "xuen");
        set_temp("owner_name", "雪凝");
        ::setup();
}
