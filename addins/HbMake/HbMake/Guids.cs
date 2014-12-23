// Guids.cs
// MUST match guids.h
using System;

namespace hb
{
    static class GuidList
    {
        public const string guidHbMakePkgString = "0a25cf6f-5c82-4716-9736-ded9bf67f407";
        public const string guidHbMakeCmdSetString = "16b873c9-b9a8-433a-8d19-11e6dacc07bd";

        public static readonly Guid guidHbMakeCmdSet = new Guid(guidHbMakeCmdSetString);
    };
}