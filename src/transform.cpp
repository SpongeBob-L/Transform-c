/*
字符集转化批处理(Linux版本)
作者：SpongeBob
联系方式:2443425920@qq.com
更新时间:2023/06/05
*/

// 采用freecplus框架
#include "_freecplus.h"

// 帮助文档
void help()
{
   printf(" --------------------\n");
   printf("|字符集转化批处理程序|\n");
   printf(" --------------------\n\n");
   printf("示例:./transform 目录名 原字符集 转化字符集 true/flase(是否删除原目录)\n\n");
   printf("copy:./transform /transform gbk utf-8 false\n\n");
}

int main(int argc,char *argv[])
{
   // 说明文档
   if( argc != 5 )
   {
      help();
      return -1;
   }

   // 判断目录是否存在
   if( opendir(argv[1]) == 0 )
   {
      printf("目录不存在\n");
      return -1;
   }

   CDir dir;   // 操作目录类

   // 打开目录
   dir.OpenDir(argv[1],"*",100000,true,false);

   // 遍历目录
   while( dir.ReadDir() )
   {
      char command_iconv[101]; // 执行命令
      char create_dir[101];    // 生成转化字符集后新的目录
      
      // 生成执行命令
      SPRINTF(command_iconv,sizeof(command_iconv),\
      "iconv -f %s -t %s %s -o %s.%s%s",\
      argv[2],argv[3],dir.m_FullFileName,argv[1],argv[3],dir.m_FullFileName+strlen(argv[1]));
      
      // 生成新的目录(目录名将为"原目录.转化字符集")
      SPRINTF(create_dir,sizeof(create_dir),\
      "%s.%s%s",argv[1],argv[3],dir.m_FullFileName+strlen(argv[1]));

      // 生成目录
      MKDIR(create_dir,true);

      // 执行命令
      printf("执行命令:%s\n",command_iconv);
      system(command_iconv);
   }

   // 判断是否删除原目录
   if( strcmp(argv[4],"true") == 0 )
   {
      char command_rm[101]; // 删除原目录命令
      char command_mv[101]; // 将目录"原目录.转化字符集"改名回原目录名命令

      // 删除原目录
      SPRINTF(command_rm,sizeof(command_rm),"rm -rf %s",argv[1]);
      printf("执行命令:%s\n",command_rm);
      system(command_rm);

      // 将目录"原目录.转化字符集"改名回原目录名
      SPRINTF(command_mv,sizeof(command_mv),"mv %s.%s %s",argv[1],argv[3],argv[1]);
      printf("执行命令:%s\n",command_mv);
      system(command_mv);
   }

   return 0;
}