#pragma once
class DX12RenderFactory :public BearRenderBase::BearRenderFactoryBase
{
	BEAR_CLASS_NO_COPY(DX12RenderFactory);
public:
	DX12RenderFactory();
	virtual ~DX12RenderFactory();
	virtual BearRenderBase::BearRenderInterfaceBase* CreateInterface();
	virtual BearRenderBase::BearRenderContextBase* CreateContext();
	virtual BearRenderBase::BearRenderViewportBase* CreateViewport(void * Handle, bsize Width, bsize Height, bool Fullscreen, bool VSync, const BearGraphics::BearRenderViewportDescription&Description);
	virtual BearRenderBase::BearRenderShaderBase* CreateShader(BearGraphics::BearShaderType Type);
	virtual  BearRenderBase::BearRenderPipelineBase*   CreatePipeline(const BearGraphics::BearRenderPipelineDescription&Descruotion);
	virtual BearRenderBase::BearRenderIndexBufferBase* CreateIndexBuffer();
	virtual BearRenderBase::BearRenderVertexBufferBase* CreateVertexBuffer();
	inline bool Empty()const { return Device.Get()==0; }
public:
	ComPtr<ID3D12Device> Device;
	ComPtr<IDXGIFactory4> GIFactory;
	ComPtr<ID3D12RootSignature> RootSignature;
	DXGI_MODE_DESC*FindMode(bsize width, bsize height);
public:
	void LockCopyCommandList();
	void UnlockCopyCommandList();
	ComPtr<ID3D12GraphicsCommandList> CopyCommandList;

	void LockCommandList();
	void UnlockCommandList();
	ComPtr<ID3D12GraphicsCommandList> CommandList;
private:
	HANDLE m_Copy_FenceEvent;
	uint64 m_Copy_FenceValue;
	ComPtr<ID3D12Fence> m_Copy_Fence;
	ComPtr<ID3D12CommandAllocator> m_Copy_CommandAllocator;
	ComPtr<ID3D12CommandQueue> m_Copy_CommandQueue;
	BearMutex m_Copy_CommandMutex;
private:
	HANDLE m_Default_FenceEvent;
	uint64 m_Default_FenceValue;
	ComPtr<ID3D12Fence> m_Default_Fence;
	ComPtr<ID3D12CommandAllocator> m_Default_CommandAllocator;
	ComPtr<ID3D12CommandQueue> m_Default_CommandQueue;
	BearMutex m_Default_CommandMutex;

	BearCore::BearVector<DXGI_MODE_DESC> m_GIVideoMode;
	void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter);
};