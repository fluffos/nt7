// This program is a part of NT MudLIB
// Master.c
//
// For ES II mudlib
// Original from Lil
// Rewritten by Annihilator (11/07/94)
// Modified by Xiang for XKX (12/15/95)
// Rewritten by Lonely@nitan.org

// #pragma optimize
// #pragma save_binary


#define BIG5_PORT                       9000
#define UTF8_PORT                       6000
#define TOMUD_PORT                      8000

//-----------------------------------------------------------------------------

#include "/adm/kernel/master/compile_object.c";        /* 用来载入 MudOS 虚拟物件 */
#include "/adm/kernel/master/crash.c";                 /* 用来处理 Crash 时的紧急情况 */
#include "/adm/kernel/master/preload.c";               /* 预先载入初始化动作 */
#include "/adm/kernel/master/error.c";                 /* 处理错误讯息的函式 */
#include "/adm/kernel/master/file.c";                  /* 关于 domain_file , author_file , privs_file */
#include "/adm/kernel/master/ed.c";                    /* 有关 Edit 的一些设定 */
#include "/adm/kernel/master/parse.c";                 /* 文法(对中文Mud而言似乎没有用处?) */
#include "/adm/kernel/master/object.c";                /* 环境遭到毁灭时, 所有内在物件都会呼叫此函式 */

//-----------------------------------------------------------------------------

#include "/adm/kernel/master/valid_asm.c";
#include "/adm/kernel/master/valid_author.c";
#include "/adm/kernel/master/valid_bind.c";            /* 检查函式指标与物件的结合 */
#include "/adm/kernel/master/valid_compile.c"          /* 判断一个文件是否可被编译 */
#include "/adm/kernel/master/valid_compile_to_c.c";    /* 判断是否可以用 LPC->C 编译 */
#include "/adm/kernel/master/valid_domain.c";
#include "/adm/kernel/master/valid_hide.c";            /* 检查匿踪能力 */
#include "/adm/kernel/master/valid_link.c";            /* 控制 link 外部函式的用途 */
#include "/adm/kernel/master/valid_object.c";          /* 让你能控制是否要载入某个物件 */
#include "/adm/kernel/master/valid_override.c";        /* 控制 efun:: 的用途 */
#include "/adm/kernel/master/valid_seteuid.c";
#include "/adm/kernel/master/valid_readwrite.c";       /* 检查是否有权读取写入档案 */
#include "/adm/kernel/master/valid_save_binary.c";     /* 控制一个物件是否可以储存它已载入的程式 */
#include "/adm/kernel/master/valid_shadow.c";          /* 控制哪些物件可以被投影 */
#include "/adm/kernel/master/valid_socket.c";          /* 保护 socket 外部函式 */
#include "/adm/kernel/master/valid_database.c";        /* 控制mysql数据库的连接 */

//-----------------------------------------------------------------------------

//        connect() 传回的物件，会当作初始使用者物件 (initial user object)。
//        请注意，之后你可以使用 exec() 外部函式将改变使用者物件。

object connect(int port)
{
        object login_ob;
        mixed err;

        err = catch(login_ob = new(LOGIN_OB));

        if( err )
        {
                debug_message("现在有人正在修改使用者连线部份的程式，请待会再来。\n");
                debug_message(err);
                destruct(this_object());
        }

        if (port == 5555)
        {
                set_encoding("GBK");
        }

        // if( port == BIG5_PORT )
        //         set_temp("big5", 1, login_ob);

        // else
        // if( port == TOMUD_PORT )
        //         set_temp("tomud", 1, login_ob);

        //else
        //if( port == UTF8_PORT )
        //      set_encoding("utf-8", login_ob);

        return login_ob;
}

string get_root_uid()
{
        return ROOT_UID;
}

string get_bb_uid()
{
        return BACKBONE_UID;
}


string object_name(object ob)
{
        if( ob ) return ob->name();
}

// 是否直接运行BINARY，不调用文件。
int direct_run_binary(string file)
{
        // object ob;
        // object vob;

#ifndef BINARY_SUPPORT
        return 0;
#else
        if( sscanf(file, DATA_DIR "%*s") )
                // 如果是DATA下面的文件，不能直接运行BIN代码，
                // 需要进行常规的版本有效检查。
                return 0;

        if( objectp(ob = find_object(CONFIG_D)) &&
            objectp(vob = find_object(VERSION_D)) ) {
                // 找到了CONFIG_D，查看本地是否是版本发布站
                // 点，如果是，则查看是否是发布的源程序，是
                // 则返回否，表示需要检查BIN。
                return query("release server", ob) != "local" &&
                       !VERSION_D->is_need_release_source(file);
        }

        // 没有找到CONFIG_D && VERSION_D，不编译，直接运行
        // BIN代码。
        return 1;
#endif
}

void create()
{
        if( clonep() )   return;

        write("master: loaded successfully.\n");
}

void check_daemons()
{
        string *sp;
        int i;

        sp = epilog(0);
        if( !sp ) return;

        for (i = 0; i < sizeof(sp); i++)
                if( stringp(sp[i])) preload(sp[i]);
}
