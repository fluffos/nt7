// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("代步而已[2;37;0m[2;37;0m", ({"daibu"}));        
        set("gender", "女性");                
        set("long", "代步而已[2;37;0m
它是洪八的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "luise");
        set("owner_name", "洪八");
        set_temp("owner", "luise");
        set_temp("owner_name", "洪八");
        ::setup();
}
