class FalseClass
  def &(other)
    false
  end

  def ^(other)
    !!other
  end

  def to_s
    "false"
  end

  alias_method :|, :^

  def inspect
    # Call #to_s rather than alias it so that people can change #to_s if they
    # wish. Yes, sounds dumb.
    to_s
  end
end

FALSE = false
