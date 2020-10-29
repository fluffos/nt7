// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m令狐小冲[2;37;0m[2;37;0m", ({"white"}));        
        set("gender", "女性");                
        set("long", "一只白老虎[2;37;0m
它是东方姑娘的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dfgn");
        set("owner_name", "东方姑娘");
        set_temp("owner", "dfgn");
        set_temp("owner_name", "东方姑娘");
        ::setup();
}
