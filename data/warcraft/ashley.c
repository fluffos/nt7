// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m艳艳[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "这鸟非常好看[2;37;0m
它是长孙无垢的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ashley");
        set("owner_name", "长孙无垢");
        set_temp("owner", "ashley");
        set_temp("owner_name", "长孙无垢");
        ::setup();
}
