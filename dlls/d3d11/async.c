/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#define COBJMACROS

#include <windows.h>
#include <stdio.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST

#include <d3d11.h>
#include <debug.h>

#include <initguid.h>

#else

#include <d3d11_2.h>
#include <wine/debug.h>

#endif

#include "thunk/qemu_d3d11.h"

#include "qemudxgi.h"
#include "qemu_d3d11.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

struct qemu_d3d11_query_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_query *impl_from_ID3D11Query(ID3D11Query *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_query, ID3D11Query_iface);
}

static inline struct qemu_d3d11_query *impl_from_ID3D10Query(ID3D10Query *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_query, ID3D10Query_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_query_QueryInterface(ID3D11Query *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_query_QueryInterface call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_QUERYINTERFACE);
    call.iface = (ULONG_PTR)query;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_QueryInterface *c = (struct qemu_d3d11_query_QueryInterface *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_QueryInterface(query->host11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_query_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_query_AddRef(ID3D11Query *iface)
{
    struct qemu_d3d11_query_AddRef call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_ADDREF);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_AddRef *c = (struct qemu_d3d11_query_AddRef *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_AddRef(query->host11);
}

#endif

struct qemu_d3d11_query_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_query_Release(ID3D11Query *iface)
{
    struct qemu_d3d11_query_Release call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_RELEASE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_Release *c = (struct qemu_d3d11_query_Release *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_Release(query->host11);
}

#endif

struct qemu_d3d11_query_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_query_GetDevice(ID3D11Query *iface, ID3D11Device **device)
{
    struct qemu_d3d11_query_GetDevice call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDEVICE);
    call.iface = (ULONG_PTR)query;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_query_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetDevice *c = (struct qemu_d3d11_query_GetDevice *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D11Query_GetDevice(query->host11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_query_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_query_GetPrivateData(ID3D11Query *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_query_GetPrivateData call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)query;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetPrivateData *c = (struct qemu_d3d11_query_GetPrivateData *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_GetPrivateData(query->host11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_query_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_query_SetPrivateData(ID3D11Query *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_query_SetPrivateData call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)query;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_SetPrivateData *c = (struct qemu_d3d11_query_SetPrivateData *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_SetPrivateData(query->host11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_query_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_query_SetPrivateDataInterface(ID3D11Query *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_query_SetPrivateDataInterface call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)query;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_SetPrivateDataInterface *c = (struct qemu_d3d11_query_SetPrivateDataInterface *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_SetPrivateDataInterface(query->host11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_query_GetDataSize
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_query_GetDataSize(ID3D11Query *iface)
{
    struct qemu_d3d11_query_GetDataSize call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDATASIZE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_GetDataSize(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetDataSize *c = (struct qemu_d3d11_query_GetDataSize *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_GetDataSize(query->host11);
}

#endif

struct qemu_d3d11_query_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_query_GetDesc(ID3D11Query *iface, D3D11_QUERY_DESC *desc)
{
    struct qemu_d3d11_query_GetDesc call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDESC);
    call.iface = (ULONG_PTR)query;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_query_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetDesc *c = (struct qemu_d3d11_query_GetDesc *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D11Query_GetDesc(query->host11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_query_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_QueryInterface(ID3D10Query *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_query_QueryInterface call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_QUERYINTERFACE);
    call.iface = (ULONG_PTR)query;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_QueryInterface *c = (struct qemu_d3d10_query_QueryInterface *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_QueryInterface(query->host10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_query_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_query_AddRef(ID3D10Query *iface)
{
    struct qemu_d3d10_query_AddRef call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_ADDREF);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_AddRef *c = (struct qemu_d3d10_query_AddRef *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_AddRef(query->host10);
}

#endif

struct qemu_d3d10_query_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_query_Release(ID3D10Query *iface)
{
    struct qemu_d3d10_query_Release call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_RELEASE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_Release *c = (struct qemu_d3d10_query_Release *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_Release(query->host10);
}

#endif

struct qemu_d3d10_query_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_GetDevice(ID3D10Query *iface, ID3D10Device **device)
{
    struct qemu_d3d10_query_GetDevice call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDEVICE);
    call.iface = (ULONG_PTR)query;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetDevice *c = (struct qemu_d3d10_query_GetDevice *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_GetDevice(query->host10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_query_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_GetPrivateData(ID3D10Query *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_query_GetPrivateData call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)query;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetPrivateData *c = (struct qemu_d3d10_query_GetPrivateData *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_GetPrivateData(query->host10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_query_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_SetPrivateData(ID3D10Query *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_query_SetPrivateData call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)query;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_SetPrivateData *c = (struct qemu_d3d10_query_SetPrivateData *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_SetPrivateData(query->host10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_query_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_SetPrivateDataInterface(ID3D10Query *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_query_SetPrivateDataInterface call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)query;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_SetPrivateDataInterface *c = (struct qemu_d3d10_query_SetPrivateDataInterface *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_SetPrivateDataInterface(query->host10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_query_Begin
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_Begin(ID3D10Query *iface)
{
    struct qemu_d3d10_query_Begin call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_BEGIN);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_Begin(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_Begin *c = (struct qemu_d3d10_query_Begin *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_Begin(query->host10);
}

#endif

struct qemu_d3d10_query_End
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_End(ID3D10Query *iface)
{
    struct qemu_d3d10_query_End call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_END);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_End(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_End *c = (struct qemu_d3d10_query_End *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_End(query->host10);
}

#endif

struct qemu_d3d10_query_GetData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_GetData(ID3D10Query *iface, void *data, UINT data_size, UINT flags)
{
    struct qemu_d3d10_query_GetData call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDATA);
    call.iface = (ULONG_PTR)query;
    call.data = (ULONG_PTR)data;
    call.data_size = data_size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_GetData(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetData *c = (struct qemu_d3d10_query_GetData *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_GetData(query->host10, QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d10_query_GetDataSize
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_query_GetDataSize(ID3D10Query *iface)
{
    struct qemu_d3d10_query_GetDataSize call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDATASIZE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_GetDataSize(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetDataSize *c = (struct qemu_d3d10_query_GetDataSize *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_GetDataSize(query->host10);
}

#endif

struct qemu_d3d10_query_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_GetDesc(ID3D10Query *iface, D3D10_QUERY_DESC *desc)
{
    struct qemu_d3d10_query_GetDesc call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDESC);
    call.iface = (ULONG_PTR)query;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetDesc *c = (struct qemu_d3d10_query_GetDesc *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_GetDesc(query->host10, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11QueryVtbl d3d11_query_vtbl =
{
    /* IUnknown methods */
    d3d11_query_QueryInterface,
    d3d11_query_AddRef,
    d3d11_query_Release,
    /* ID3D11DeviceChild methods */
    d3d11_query_GetDevice,
    d3d11_query_GetPrivateData,
    d3d11_query_SetPrivateData,
    d3d11_query_SetPrivateDataInterface,
    /* ID3D11Asynchronous methods */
    d3d11_query_GetDataSize,
    /* ID3D11Query methods */
    d3d11_query_GetDesc,
};

static struct ID3D10QueryVtbl d3d10_query_vtbl =
{
    /* IUnknown methods */
    d3d10_query_QueryInterface,
    d3d10_query_AddRef,
    d3d10_query_Release,
    /* ID3D10DeviceChild methods */
    d3d10_query_GetDevice,
    d3d10_query_GetPrivateData,
    d3d10_query_SetPrivateData,
    d3d10_query_SetPrivateDataInterface,
    /* ID3D10Asynchronous methods */
    d3d10_query_Begin,
    d3d10_query_End,
    d3d10_query_GetData,
    d3d10_query_GetDataSize,
    /* ID3D10Query methods */
    d3d10_query_GetDesc,
};

#else

#endif
