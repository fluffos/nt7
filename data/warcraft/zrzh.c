// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m武[1;34m[1;36m藤[1;36m[1;33m兰[1;33m[2;37;0m[2;37;0m", ({"lan"}));        
        set("gender", "女性");                
        set("long", "AV[2;37;0m
它是粽星的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zrzh");
        set("owner_name", "粽星");
        set_temp("owner", "zrzh");
        set_temp("owner_name", "粽星");
        ::setup();
}
