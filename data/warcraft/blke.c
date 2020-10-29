// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"luobu"}));        
        set("gender", "女性");                
        set("long", "这是一只朱雀[2;37;0m
它是哥哥疯了的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "blke");
        set("owner_name", "哥哥疯了");
        set_temp("owner", "blke");
        set_temp("owner_name", "哥哥疯了");
        ::setup();
}
