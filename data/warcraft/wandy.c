// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m七喜[2;37;0m[2;37;0m", ({"wandyy"}));        
        set("gender", "女性");                
        set("long", "$HIW$七喜[2;37;0m
它是小手冰凉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wandy");
        set("owner_name", "小手冰凉");
        set_temp("owner", "wandy");
        set_temp("owner_name", "小手冰凉");
        ::setup();
}
