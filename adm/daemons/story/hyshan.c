// story:hushan 火焰山传说

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "白骨精：牛哥！",
        "牛魔王：干啥？",
        "白骨精：牛哥，你可得给我做主啊！",
        "牛魔王：谁欺负你了？",
        "白骨精：还，还不是你那个义弟...",
        "牛魔王：义弟？哪个义弟？",
        "牛魔王暗想：我好象有好几百个义弟吧，这说的是那一个啊？",
        "白骨精呜咽道：就是那个孙猴子啊。",
        "牛魔王大怒：你说的是那猴子？哼！他先坑害我儿子，后又欺负你嫂子...",
        "牛魔王想了想又道：骗走我的芭蕉扇，我已经把他开除了！",
        "白骨精大喜道：那你可要替我报仇啊，我刚被他欺负！",
        "牛魔王道：不忙，我这就找上几个弟兄，去替你报仇！",
        "......",
        (: give_gift, "niutou" :),
        "听说牛魔王派出牛头怪(niutou guai)，下了火焰山。",
});

string prompt() { return HIM "【神话】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出现在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
