// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小璐璐[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "女性");                
        set("long", "上古魔兽[2;37;0m
它是张璐璐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cjq");
        set("owner_name", "张璐璐");
        set_temp("owner", "cjq");
        set_temp("owner_name", "张璐璐");
        ::setup();
}
