// broadcastd.c

#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

mapping push_msg = ([]);
string query_save_file() { return DATA_DIR + "broadcastd"; }

/* 临时通过pushmsg 指令推送的广播消息
格式：
push_msg = ([
   "msg编号" :  ([
      "广播内容"       : "xxx",
      "间隔时间"       : N, // 单位秒
      "循环次数"       : N, // int
      "上次广播时间：  : TIME,
      "已循环次数"     : N, // int
   ]),
]);
*/
void create()
{
        seteuid(getuid());
        set("channel_id", "广播精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "广播精灵已经启动。");

        if( !restore() && !mapp(push_msg) )
                push_msg = ([]);

        SCHEDULE_D->set_event(10, 1, this_object(), "broadcast_push_msg");
}

void broadcast_push_msg()
{
        string *key;
        int i;

        if (! sizeof(push_msg))return;

        key = keys(push_msg);

        for (i = 0; i < sizeof(key); i ++)
        {
                if( time() - push_msg[key[i]]["last_broadcast"] < push_msg[key[i]]["delay"] )
                        continue;

                if( push_msg[key[i]]["broadcast_times"] >= push_msg[key[i]]["times"] )
                        continue;

                message_system(HIW + push_msg[key[i]]["msg"] + "\n" NOR);
                push_msg[key[i]]["last_broadcast"] = time();
                push_msg[key[i]]["broadcast_times"] += 1;
        }
        return;
}

public int add_push_msg(string title, string info, int delay, int times)
{
        string *key;

        if (! sizeof(push_msg)) key = ({});
        else
                key = keys(push_msg);

        // 检查标题是否重复
        if (sizeof(key))
        {
                if (member_array(title, key) != -1)
                        return notify_fail("标题重复！\n");
        }

        if (sizeof(info) > 300)
                return notify_fail("信息长度超长" + sprintf("%d", sizeof(info) - 88) + "个字符！\n");

        if (delay < 1)
                return notify_fail("间隔时间不能低于1秒。\n");

        if (times < 1)
                return notify_fail("循环次数不能小于1。\n");

        if( !mapp(push_msg) ) push_msg = ([]);
        push_msg += ([
              title : ([
                  "msg"       : info,
                  "delay"     : delay, // 单位秒
                  "times"     : times,
                  "last_broadcast"   : 0,
                  "broadcast_times"  : 0,
              ])
        ]);

        save();
        write("添加成功！使用指令 pushmsg list 查看当前信息列表。\n");
        return 1;
}

public int show_push_lish()
{
        string *key, msg;
        int i;

        msg = HIC "\n=----------------------------------------=\n" NOR;

        if (! sizeof(push_msg))
                return notify_fail("当前没有PUSHMSG信息！\n");

        key = keys(push_msg);

        for (i = 0; i < sizeof(key); i ++)
        {
                msg += HIY "[" + key[i] + "]    " HIC + "间隔" + sprintf("%d", push_msg[key[i]]["delay"]) + "秒    " +
 "循环" + sprintf("%d/%d", push_msg[key[i]]["broadcast_times"],push_msg[key[i]]["times"] ) + "\n" NOR;
            msg += HIY "内容：" + HIC + push_msg[key[i]]["msg"] + "\n\n";
        }
        msg += HIC "\n=----------------------------------------=\n" NOR;
        msg += HIR "指令 pushmsg del [TITLE] 可删除广播！\n" NOR;

        write(msg);
        return 1;
}

public int delete_push_msg(string title)
{
        string *key;

        if (! sizeof(push_msg))key = ({});
        else
                key = keys(push_msg);

        // 检查标题是否重复
        if (sizeof(key))
        {
                if (member_array(title, key) == -1)
                        return notify_fail("无此标题！\n");
        }
        else
                return notify_fail("当前无PUSHMSG！\n");

        map_delete(push_msg, title);

        write(title + " del OK.\n");
        save();
        return 1;
}

void reback_lonely_book()
{
        mixed *file;
        int iCount;
        string *t;
        object book;

        remove_call_out("reback_lonely_book");
        call_out("reback_lonely_book", 3600*24); // 24小时回收一次

        file = get_dir("/clone/lonely/book/", -1);

        message_system(HIW "系统回收唯一物品。\n" NOR);

        for (iCount = 0; iCount < sizeof(file); iCount ++)
        {
                book = find_object("/clone/lonely/book/" + file[iCount][0]);
                if (objectp(book))destruct(book);
        }
        // 乾坤大挪移
        book = find_object("/clone/book/qiankun_book" );
        if (objectp(book))destruct(book);

        return;
}

int remove()
{
        save();
        return 1;
}

