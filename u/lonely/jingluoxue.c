#include <ansi.h>

#define XBOOK_DIR "/clone/lonely/book/"
int get_book();
int get_book2();

nosave mixed *story = ({
        "王语焉：公子，听说表哥正在修炼参合指，欲找你报仇，你的六脉神剑也修炼一下吧！",
        "段誉：这个.........",
        "段誉：冤家宜解不宜结，何况凶殴斗杀，有违国法，若教官府知道，大大的不便。",
        "木婉清：.............真是一块烂木头！",
        "钟灵：难道慕容公子要抢走王姐姐你也不管么？？？",
        "段誉：这个...这个...",
        "王语焉：你真的不管！！！",
        "段誉：不是不是，只是我家经络学流落江湖，缺了它，无法修炼啊！",
        "木婉清：这倒是无妨，明天我们就重出江湖，寻找经络学！！",
        "钟灵：好啊好啊，正好出去玩玩！",
        "段誉：啊！你们都去！！！",
        "木婉清：当然！不然放你一个人出去，不知又找几个姐姐回来！",
        "段誉：................",
        "数日后",
        (: get_book :),
        "段誉：这位兄台，小生段誉，我家经络学你也看了许久，不知可否送还于我？",
        "某人：..........",
        "木婉清：跟他废话这么多！！看我的袖箭！！",
                (: get_book2 :),
        "某人惨叫一声：啊！",
        "听说某人惨遭毒手，经络学被夺！",
});

string *books = ({
        "jingluoxue1",
        "jingluoxue2",
        });

string prompt() { return HIW "【武林轶事】" NOR; }

object ob;

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int get_book()
{
        int i = random(2);

        ob = find_object(XBOOK_DIR + books[i]);
                if(!objectp(ob)) ob = find_object(XBOOK_DIR + books[!i]);
                if(!objectp(ob)) {
                        story = allocate(20);
                        story[15] = "段誉：这几日游历了大好河山，实乃快哉！";
                        story[16] = "木婉清：书都没有找到，就知道玩，没出息。";
                        story[17] = "钟灵：嘻嘻，不会呀，我觉得这些天玩的蛮开心的。";
                        story[18] = "段誉：还是灵儿最知我心意。";
                        story[19] = "段誉一行人最后无功而反。";
                }
                return 1;
}

int get_book2()
{
        object owner;
        if(objectp(environment(ob)) && userp(environment(ob))) {
                owner = environment(ob);
                tell_object(owner, "只见一道寒光，一根袖箭正中你胸口。\n");
                owner->unconcious();
        }
        destruct(ob);
                return 1;
}
