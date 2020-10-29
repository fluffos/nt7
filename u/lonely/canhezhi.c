#include <ansi.h>

#define BOOK_DIR "/clone/lonely/book/"
int get_book();

nosave mixed *story = ({
        "少林英雄大会后，姑苏燕子坞",
        "慕容复：段誉这小子太可恨了！居然这样羞辱我！",
        "邓百川：可是他的六脉神剑实在厉害呀！",
        "包不同：非也非也，我慕容家的参合指并不输于六脉神剑。",
        "慕容复：事到如今，只能强行修炼参合指了！",
        "公冶乾：可是公子，听说修炼参合指所需的八种指法秘籍已流落江湖，不知在何人之手。",
        "风波恶：无妨，明日我四人就出庄寻找，誓为公子取得秘籍！",
        (: get_book :),
        "数日后",
});

string *books = ({
        "lianhuazhi",
        "qixingzhi",
        "tianlongzhi",
        "qilian",
        "youmingzhi",
        "tianzhuzhi",
        "duoluoyezhi",
        "xiuluozhi",
        });

string *finder = ({"邓百川", "包不同", "公冶乾", "风波恶"});

string prompt() { return HIW "【武林轶事】" NOR; }

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
        object ob, book, owner;
        int i = sizeof(books);
        string temp, *find_book = ({});

        while(i--) {
                ob = find_object(BOOK_DIR + books[i]);
                if(objectp(ob)) {
                        find_book += ({ob->name()});
                        if(objectp(environment(ob)) && userp(environment(ob))) {
                                owner = environment(ob);
                                tell_object(owner, "你突然被感到后脑一痛，好像被硬物打了一下。\n");
                                owner->unconcious();
                        }
                        destruct(ob);
                                }
        }
        if (! i = sizeof(find_book)) {
                story += ({finder[random(sizeof(finder))] + "：公子，属下无能，在江湖上浪荡这么久也没有为你找到一本秘笈。"});
                story += ({"慕容复：这不怪你，因为我已经收集到修炼所有秘笈了。"});
        } else {
                temp = find_book[--i];
                if(i) {
                        while(--i) temp += "、" + find_book[i];
                        temp += "及" + find_book[0];
                }
                story += ({finder[random(4)] + "：公子，我找到了" + temp + "，你看！"});
                story += ({"慕容复：太好了，看来我练成参合指有望了。"});
        }
        return 1;
}