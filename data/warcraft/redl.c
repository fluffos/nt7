// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[46m[1;37m九尾狐狸精[2;37;0m[2;37;0m", ({"foxtrel"}));        
        set("gender", "女性");                
        set("long", "一只善解人意，温馨漂亮的狐狸精。[2;37;0m
它是红莲老祖的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "redl");
        set("owner_name", "红莲老祖");
        set_temp("owner", "redl");
        set_temp("owner_name", "红莲老祖");
        ::setup();
}
